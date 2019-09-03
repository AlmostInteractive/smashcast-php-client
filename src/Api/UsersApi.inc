<?php

declare(strict_types=1);

namespace SmashcastApi\Api;


use GuzzleHttp\Exception\GuzzleException;
use Psr\Http\Message\ResponseInterface;

class UsersApi extends AbstractApiBase
{
    /**
     * @throws GuzzleException
     */
    public function getUserByAuthToken(string $authToken): ?string
    {
        $response = $this->apiGet("userfromtoken/$authToken");
        $userData = json_decode($response->getBody()->getContents(), true);

        return $userData['user_name'] ?? null;
    }

    /**
     * @throws GuzzleException
     */
    public function getUserInfo(string $userId, ?string $authToken = null): ?array
    {
        $response = $this->apiGet("user/$userId", [], $authToken);
        $userInfo = json_decode($response->getBody()->getContents(), true);
        return isset($userInfo['user_name']) ? $userInfo : null;
    }
}
